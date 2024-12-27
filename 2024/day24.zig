const std = @import("std");

const PART = 2;

const GateType = enum { And, Or, Xor };

const Wire = struct {
    name: []const u8,
    value: ?bool,
};

const Gate = struct {
    type: GateType,
    input: [2] *Wire,
    output: *Wire
};

const BinaryAdder = struct { 
    wires: std.StringHashMap(*Wire), 
    gates: std.StringHashMap(*Gate) 
};

fn findOrAddWire(name: []const u8, adder: *BinaryAdder, alloc: std.mem.Allocator) !*Wire {
    if (adder.wires.get(name)) |wire| return wire;

    const new_wire = try alloc.create(Wire);
    new_wire.* = .{
        .name = name,
        .value = null
    };
    try adder.wires.put(name, new_wire);
    return new_wire;
}

fn createAdder(data: []const u8, alloc: std.mem.Allocator) !*BinaryAdder {
    const result = try alloc.create(BinaryAdder);
    result.* = .{ 
        .wires = std.StringHashMap(*Wire).init(alloc), 
        .gates = std.StringHashMap(*Gate).init(alloc) 
    };

    var lines = std.mem.splitScalar(u8, data, '\n');
    while (lines.next()) |line| {
        if (line.len == 0) {
            break;
        }

        var parts = std.mem.splitSequence(u8, line, ": ");
        const name = parts.first();
        const wire = try alloc.create(Wire);
        wire.* = .{ 
            .name = name, 
            .value = std.mem.eql(u8, parts.next() orelse "", "1") 
        };
        try result.wires.put(name, wire);
    }

    while (lines.next()) |line| {
        var params = std.ArrayList([]const u8).init(alloc);
        defer params.deinit();

        var parts = std.mem.splitScalar(u8, line, ' ');
        while (parts.next()) |part| {
            try params.append(part);
        }

        std.debug.assert(params.items.len == 5);

        const input1 = params.items[0];
        const input2 = params.items[2];
        const output = params.items[4];
        const gate_type: GateType = switch (params.items[1][0]) {
            'A' => .And,
            'O' => .Or,
            'X' => .Xor,
            else => unreachable
        };

        // register output wire of gate. if a dummy was created before we just initialize it now
        const output_wire = result.wires.get(output) orelse try alloc.create(Wire);
        output_wire.* = .{
            .name = output,
            .value = null
        };
        try result.wires.put(output, output_wire);

        const gate= try alloc.create(Gate);
        gate.* = .{
            .type = gate_type,
            .input = .{
                try findOrAddWire(input1, result, alloc),
                try findOrAddWire(input2, result, alloc),
            },
            .output = output_wire,
        };
        try result.gates.put(output, gate);
    }

    return result;
}

fn deinitAdder(adder: *BinaryAdder, alloc: std.mem.Allocator) void {
    var wires = adder.wires.valueIterator();
    while (wires.next()) |item| {
        alloc.destroy(item.*);
    }
    adder.wires.deinit();

    var gates = adder.gates.valueIterator();
    while (gates.next()) |item| {
        alloc.destroy(item.*);
    }
    adder.gates.deinit();

    alloc.destroy(adder);
}

fn resolveGateOutput(adder: *BinaryAdder, gate: *Gate) u1 {
    if (gate.output.value) |value| {
        return @intFromBool(value);
    }

    var values: [2]u1 = .{0, 0};
    for (0..2) |i| {
        if (adder.gates.get(gate.input[i].name)) |input_gate| {
            values[i] = resolveGateOutput(adder, input_gate);
        } else {
            const wire = adder.wires.get(gate.input[i].name);
            std.debug.assert(wire != null and wire.?.value != null);
            values[i] = @intFromBool(wire.?.value.?);
        }
    }

    return switch (gate.type) {
        .And => values[0] & values[1],
        .Or  => values[0] | values[1],
        .Xor => values[0] ^ values[1]
    };
}

fn part1(adder: *BinaryAdder) !void {
    var sum: u64 = 0;
    var gates = adder.gates.valueIterator();
    while (gates.next()) |gate_ptr| {
        const gate = gate_ptr.*;
        if (gate.output.name[0] == 'z') {
            const bit = try std.fmt.parseInt(u6, gate.output.name[1..], 10);
            sum |= @as(u64, resolveGateOutput(adder, gate)) << bit;
        }
    }

    std.debug.print("{d}\n", .{sum});
}

fn validateGate(name: []const u8, adder: *BinaryAdder, gate: *Gate) !bool {
    if (name[0] == 'z') {
        const bit = try std.fmt.parseInt(u6, gate.*.output.name[1..], 10);
        return bit >= 45 or gate.type == .Xor;
    }

    if (gate.type == .Xor) {
        const  gate_ok = ((gate.input[0].name[0] == 'x' or gate.input[0].name[0] == 'y') and
                                (gate.input[1].name[0] == 'x' or gate.input[1].name[0] == 'y')) or
                                (gate.output.name[0] == 'z');
        if (!gate_ok) {
            return false;
        }

        var gates = adder.gates.valueIterator();
        while (gates.next()) |gate_ptr| {
            const next_gate = gate_ptr.*;
            if (next_gate.type == GateType.Or and 
               (std.mem.eql(u8, next_gate.input[0].name, name) or std.mem.eql(u8, next_gate.input[1].name, name))) {
                return false;
            }
        }
    }

    if (gate.type == GateType.And and !std.mem.eql(u8, gate.input[0].name, "x00") and !std.mem.eql(u8, gate.input[1].name, "x00")) {
        var gates = adder.gates.valueIterator();
        while (gates.next()) |gate_ptr| {
            const next_gate = gate_ptr.*;
            if (next_gate.type != GateType.Or and 
               (std.mem.eql(u8, next_gate.input[0].name, name) or std.mem.eql(u8, next_gate.input[1].name, name))) {
                return false;
            }
        }
    }

    return true;
}

fn stringLessThan(_: void, lhs: []const u8, rhs: []const u8) bool {
    return std.mem.order(u8, lhs, rhs) == .lt;
}

fn part2(adder: *BinaryAdder, alloc: std.mem.Allocator) !void {
    var result = std.ArrayList([]const u8).init(alloc);
    defer result.deinit();

    var gates = adder.gates.iterator();
    while (gates.next()) |item| {
        if (!try validateGate(item.key_ptr.*, adder, item.value_ptr.*)) {
            try result.append(item.key_ptr.*);
        }
    }

    std.mem.sort([]const u8, result.items, {}, stringLessThan);

    for (result.items) |item| {
        std.debug.print("{s},", .{item});
    }
}

pub fn main() void {
    const data =
        \\x00: 1
        \\x01: 0
        \\x02: 1
        \\x03: 1
        \\x04: 0
        \\x05: 0
        \\x06: 1
        \\x07: 1
        \\x08: 0
        \\x09: 1
        \\x10: 1
        \\x11: 1
        \\x12: 1
        \\x13: 0
        \\x14: 0
        \\x15: 1
        \\x16: 0
        \\x17: 0
        \\x18: 1
        \\x19: 1
        \\x20: 1
        \\x21: 1
        \\x22: 0
        \\x23: 0
        \\x24: 1
        \\x25: 0
        \\x26: 1
        \\x27: 1
        \\x28: 0
        \\x29: 0
        \\x30: 1
        \\x31: 1
        \\x32: 0
        \\x33: 1
        \\x34: 1
        \\x35: 0
        \\x36: 0
        \\x37: 0
        \\x38: 0
        \\x39: 1
        \\x40: 0
        \\x41: 1
        \\x42: 1
        \\x43: 0
        \\x44: 1
        \\y00: 1
        \\y01: 0
        \\y02: 0
        \\y03: 1
        \\y04: 1
        \\y05: 0
        \\y06: 0
        \\y07: 0
        \\y08: 0
        \\y09: 0
        \\y10: 0
        \\y11: 1
        \\y12: 0
        \\y13: 1
        \\y14: 1
        \\y15: 0
        \\y16: 1
        \\y17: 0
        \\y18: 1
        \\y19: 0
        \\y20: 1
        \\y21: 0
        \\y22: 1
        \\y23: 0
        \\y24: 0
        \\y25: 0
        \\y26: 0
        \\y27: 0
        \\y28: 0
        \\y29: 0
        \\y30: 1
        \\y31: 1
        \\y32: 1
        \\y33: 1
        \\y34: 0
        \\y35: 0
        \\y36: 0
        \\y37: 1
        \\y38: 1
        \\y39: 0
        \\y40: 1
        \\y41: 1
        \\y42: 0
        \\y43: 0
        \\y44: 1
        \\
        \\x01 XOR y01 -> fht
        \\cpg OR qrh -> wtp
        \\wtk XOR thb -> z30
        \\mrj OR cbd -> bjr
        \\y12 XOR x12 -> kng
        \\hrh AND chp -> bgc
        \\qkp XOR ggh -> z36
        \\x24 XOR y24 -> mqt
        \\jbp AND qsw -> dhs
        \\kng XOR jqh -> z12
        \\x21 XOR y21 -> rvk
        \\qqd AND hfb -> qmd
        \\ggh AND qkp -> svm
        \\y26 AND x26 -> bch
        \\mms AND qsf -> cvm
        \\kdt AND rqf -> mrj
        \\jrg OR kqm -> ngk
        \\y43 XOR x43 -> fns
        \\x10 XOR y10 -> jkn
        \\hjc XOR cgv -> z09
        \\swm OR wjb -> cgv
        \\y17 AND x17 -> fvk
        \\qsw XOR jbp -> z44
        \\y01 AND x01 -> dmk
        \\y29 XOR x29 -> gnj
        \\x32 XOR y32 -> qqd
        \\x25 XOR y25 -> cbd
        \\y23 AND x23 -> bvb
        \\dvj AND bjg -> djv
        \\dbv XOR bcm -> z03
        \\x02 XOR y02 -> qdt
        \\qqv OR qkh -> nqr
        \\tmh AND bjr -> cjf
        \\knp XOR nvr -> z08
        \\rmc XOR hdk -> z42
        \\y07 XOR x07 -> mms
        \\nqr AND jtk -> jgf
        \\y18 AND x18 -> qdp
        \\x31 AND y31 -> cbh
        \\x06 AND y06 -> z06
        \\wwt OR rjp -> bkk
        \\y17 XOR x17 -> ptj
        \\y14 XOR x14 -> fgr
        \\y11 XOR x11 -> tsh
        \\fhk XOR bkq -> z28
        \\kkg AND nwg -> jpt
        \\y03 AND x03 -> qkh
        \\tmh XOR bjr -> z26
        \\rkw OR pww -> kdt
        \\tfn AND qgq -> jgt
        \\nrs XOR qdt -> z02
        \\kgw OR rds -> bjg
        \\fcb OR hnr -> jbp
        \\y38 AND x38 -> cpg
        \\rqf XOR kdt -> z25
        \\y12 AND x12 -> fcd
        \\pnh XOR jsp -> z27
        \\hfb XOR qqd -> z32
        \\ftc OR fjm -> bkq
        \\y05 XOR x05 -> pvt
        \\cjt XOR sfm -> jmq
        \\x27 XOR y27 -> jsp
        \\rrt AND cjs -> nsb
        \\hjc AND cgv -> dfj
        \\x34 AND y34 -> qtd
        \\x00 AND y00 -> nqp
        \\qvh AND cgj -> mmm
        \\x21 AND y21 -> vfv
        \\gts XOR cvg -> z16
        \\x38 XOR y38 -> njc
        \\pbb OR mkc -> bcm
        \\hct OR hmc -> wbt
        \\rvk XOR jgk -> z21
        \\cjt AND sfm -> fmd
        \\svm OR bbb -> nsf
        \\dmk OR ntf -> nrs
        \\y44 XOR x44 -> qsw
        \\x36 XOR y36 -> qkp
        \\x27 AND y27 -> ftc
        \\gbd OR fjv -> z13
        \\nmh OR nsb -> jgk
        \\rjj OR fvk -> nwg
        \\qqj OR vwp -> pqg
        \\x04 AND y04 -> bwb
        \\mqt AND ssw -> rkw
        \\y30 XOR x30 -> thb
        \\bdc AND pvt -> chv
        \\wrj AND njp -> kqf
        \\jtk XOR nqr -> z04
        \\gqf OR qtd -> njp
        \\njc AND ngk -> z38
        \\x39 AND y39 -> rds
        \\x10 AND y10 -> hct
        \\hch AND dmm -> bhs
        \\dvj XOR bjg -> z40
        \\y24 AND x24 -> pww
        \\y03 XOR x03 -> dbv
        \\y28 XOR x28 -> fhk
        \\nmm XOR kwb -> gmh
        \\vfv OR qpp -> pjk
        \\gvt AND qpm -> rbf
        \\rrt XOR cjs -> z20
        \\pvt XOR bdc -> z05
        \\y31 XOR x31 -> hrh
        \\y40 XOR x40 -> dvj
        \\y28 AND x28 -> ghp
        \\y22 AND x22 -> stn
        \\nwg XOR kkg -> z18
        \\ptw AND pjk -> cpb
        \\cbh OR bgc -> hfb
        \\x18 XOR y18 -> kkg
        \\x35 XOR y35 -> wrj
        \\vmr OR mwp -> srh
        \\tsh AND wbt -> dwn
        \\mpv XOR wtp -> z39
        \\y34 XOR x34 -> hvf
        \\y19 AND x19 -> gqg
        \\fcd OR bnt -> kwb
        \\hdk AND rmc -> vwp
        \\nbk OR knk -> chp
        \\x30 AND y30 -> nbk
        \\qmn OR kqf -> ggh
        \\gts AND cvg -> mwp
        \\tfn XOR qgq -> z19
        \\x33 AND y33 -> rjp
        \\nrs AND qdt -> mkc
        \\y36 AND x36 -> bbb
        \\wbt XOR tsh -> z11
        \\kjv OR dfj -> whc
        \\mvf OR mmm -> rmc
        \\pnh AND jsp -> fjm
        \\x11 AND y11 -> mfr
        \\cvm OR sbj -> knp
        \\jgt OR gqg -> cjs
        \\x08 XOR y08 -> nvr
        \\y39 XOR x39 -> mpv
        \\tmm AND wqn -> wwt
        \\qmd OR wtb -> tmm
        \\fgr AND gmh -> ckd
        \\wrj XOR njp -> z35
        \\wdq OR hrf -> wtk
        \\y42 XOR x42 -> hdk
        \\jqh AND kng -> bnt
        \\bvb OR rbf -> ssw
        \\cgj XOR qvh -> z41
        \\x13 XOR y13 -> nmm
        \\ptj AND srh -> rjj
        \\x13 AND y13 -> fjv
        \\x43 AND y43 -> hnr
        \\hvf XOR bkk -> z34
        \\x15 XOR y15 -> hch
        \\y14 AND x14 -> cqb
        \\fmd OR jmq -> qsf
        \\ngk XOR njc -> qrh
        \\x41 XOR y41 -> cgj
        \\x07 AND y07 -> sbj
        \\nmm AND kwb -> gbd
        \\gmh XOR fgr -> z14
        \\gnj XOR bcv -> z29
        \\y32 AND x32 -> wtb
        \\x08 AND y08 -> swm
        \\y29 AND x29 -> wdq
        \\pqg XOR fns -> z43
        \\ndr AND nsf -> jrg
        \\bcm AND dbv -> qqv
        \\jgk AND rvk -> qpp
        \\gvt XOR qpm -> z23
        \\x22 XOR y22 -> ptw
        \\y02 AND x02 -> pbb
        \\jpt OR qdp -> qgq
        \\nsf XOR ndr -> z37
        \\bhs OR msb -> cvg
        \\y09 AND x09 -> kjv
        \\dwn OR mfr -> jqh
        \\x35 AND y35 -> qmn
        \\jgf OR bwb -> bdc
        \\y09 XOR x09 -> hjc
        \\pjk XOR ptw -> z22
        \\x19 XOR y19 -> tfn
        \\bcv AND gnj -> hrf
        \\x16 AND y16 -> vmr
        \\srh XOR ptj -> z17
        \\y40 AND x40 -> wgw
        \\x04 XOR y04 -> jtk
        \\jkn AND whc -> hmc
        \\chp XOR hrh -> z31
        \\cpb OR stn -> qpm
        \\y42 AND x42 -> qqj
        \\fhk AND bkq -> mtn
        \\y37 XOR x37 -> ndr
        \\fht XOR nqp -> z01
        \\x25 AND y25 -> rqf
        \\fns AND pqg -> fcb
        \\tmm XOR wqn -> z33
        \\cjf OR bch -> pnh
        \\x23 XOR y23 -> gvt
        \\mms XOR qsf -> z07
        \\hvf AND bkk -> gqf
        \\x33 XOR y33 -> wqn
        \\y37 AND x37 -> kqm
        \\y15 AND x15 -> msb
        \\x20 AND y20 -> nmh
        \\wtk AND thb -> knk
        \\mtn OR ghp -> bcv
        \\wvm OR dhs -> z45
        \\wgw OR djv -> qvh
        \\ckd OR cqb -> dmm
        \\x41 AND y41 -> mvf
        \\y05 AND x05 -> smt
        \\hch XOR dmm -> z15
        \\y44 AND x44 -> wvm
        \\smt OR chv -> cjt
        \\knp AND nvr -> wjb
        \\x06 XOR y06 -> sfm
        \\x26 XOR y26 -> tmh
        \\wtp AND mpv -> kgw
        \\y20 XOR x20 -> rrt
        \\ssw XOR mqt -> z24
        \\nqp AND fht -> ntf
        \\y00 XOR x00 -> z00
        \\jkn XOR whc -> z10
        \\y16 XOR x16 -> gts
    ;

    var gpa = std.heap.GeneralPurposeAllocator(.{}){};
    const alloc = gpa.allocator();

    const adder = createAdder(data, alloc) catch unreachable;
    defer deinitAdder(adder, alloc);

    if (PART == 1) {
        part1(adder) catch unreachable;
    } else {
        part2(adder, alloc) catch unreachable;
    }
}
