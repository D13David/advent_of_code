class AocScriptedTexture expands ClientScriptedTexture;

var() Font Font;
var() color FontColor;
var() int PixelsPerSecond;
var() int ScrollWidth;
var() float YPos;

var string DisplayText;
var int Position;
var float LastDrawTime;

struct I64
{
  var int high;
  var int low;
};

struct VmContext
{
  var I64     RegA;
  var I64     RegB;
  var I64     RegC;
  var int     IP;
  var string  Prg;
};

var VmContext Context;

//-----------------------------------------------------------------------------
// unusual huge number math utils for christmas 3-bit(tm)
function I64 Set64(int high, int low)
{
  local I64 result;
  result.high = high;
  result.low = low;
  return result;
}

function I64 ShiftRight64(I64 value, int shift)
{
  local I64 result;
  result.low  = (value.low >>> shift) | (value.high << (32 - shift));
  result.high = (value.high >>> shift);
  return result;
}

function I64 ShiftLeft64(I64 value, int shift)
{
  local I64 result;
  result.high  = (value.high << shift) | (value.low >>> (32 - shift));
  result.low = (value.low << shift);
  return result;
}

function I64 ExclusiveOr64(I64 value1, I64 value2)
{
  local I64 result;
  result.low = value1.low ^ value2.low;
  result.high = value1.high ^ value2.high;
  return result;
}

function I64 Or64(I64 value1, I64 value2)
{
  local I64 result;
  result.low = value1.low | value2.low;
  result.high = value1.high | value2.high;
  return result;
}

function I64 And64(I64 value1, I64 value2)
{
  local I64 result;
  result.low = value1.low & value2.low;
  result.high = value1.high & value2.high;
  return result;
}

function bool IsZero64(I64 value)
{
  return value.high == 0 && value.low == 0;
}

//-----------------------------------------------------------------------------
// christmas 3-bit(tm) vm
function ResetVm(I64 regA, I64 regB, I64 RegC, string prg)
{
  Context.RegA = regA;
  Context.RegB = regB;
  Context.RegC = regC;
  Context.IP   = 0;
  Context.Prg  = prg;
}

function int ResolveComboParam(int value)
{
  switch (value)
  {
    case 0:
    case 1:
    case 2:
    case 3:
      return value;
    case 4:
      return Context.RegA.low;
    case 5:
      return Context.RegB.low;
    case 6:
      return Context.RegC.low;
  }

  return 0;
}

function string Run()
{
  local int prgLength;
  local int i;
  local int op;
  local int param;
  local string output;

  prgLength = Len(Context.Prg);
  
  while (Context.IP < prgLength)
  {
    op = int(Mid(Context.Prg, Context.IP, 1));
    param = int(Mid(Context.Prg, Context.IP+1, 1));
    switch (op)
    {
      case 0 /*ADV*/:
        Context.RegA = ShiftRight64(Context.RegA, ResolveComboParam(param));
        break;
      case 1 /*BXL*/:
        Context.RegB = ExclusiveOr64(Context.RegB, Set64(0, param));
        break;
      case 2 /*BST*/:
        Context.RegB = Set64(0, ResolveComboParam(param) & 7);
        break;
      case 3 /*JNZ*/:
        if (!IsZero64(Context.RegA)) {
          Context.IP = param - 2;
        }
        break;
      case 4 /*BXC*/:
        Context.RegB = ExclusiveOr64(Context.RegB, Context.RegC);
        break;
      case 5 /*OUT*/:
        output = output $ (Context.RegB.low & 7) $ ", ";
        break;
      case 6 /*BDV*/:
        Context.RegB = ShiftRight64(Context.RegA, ResolveComboParam(param));
        break;
      case 7 /*CDV*/:
        Context.RegC = ShiftRight64(Context.RegA, ResolveComboParam(param));
        break;
    }
    
    Context.IP += 2;
  }
  
  return Mid(output, 0, Len(output)-1);
}

function I64 RestoreRegisterValue(string program)
{
  local I64 values[128];
  local I64 candidates[128];
  local int numValues, numCandidates;
  local int currentValue, bits, i;
  local I64 B, C, Next;
  
  /***
   *00: bst 4     ; B = A & 7
   *02: bxl 1     ; B = B ^ 1
   *04: cdv 5     ; C = A >> B
   *06: adv 3     ; A = A >> 3 
   *08: bxl 4     ; B = B ^ 4
   *0A: bxc 5     ; B = B ^ C
   *0C: out 5     ; OUT = B & 7
   *0E: jnz 0     ; goto 00 if A != 0
   **/
   
  values[numValues++] = Set64(0, 0);
  
  for (i = Len(program)-1; i >= 0; --i)
  {
    numCandidates = 0;
    
    for (currentValue = 0; currentValue < numValues; ++currentValue)
    {
      for (bits = 0; bits < 8; ++bits)
      {
        Next = Or64(ShiftLeft64(values[currentValue], 3), Set64(0, bits));
        
        // run program logic
        B = And64(Next, Set64(0, 7));
        B = ExclusiveOr64(B, Set64(0, 1));
        C = ShiftRight64(Next, B.low);
        // A = A >> 3
        B = ExclusiveOr64(B, Set64(0, 4));
        B = ExclusiveOr64(B, C);
        
        if ((B.low & 7) == int(Mid(program, i, 1))) 
        {
            candidates[numCandidates++] = Next;
        }
      }
    }
    
    numValues = 0;
    for (currentValue = 0; currentValue < numCandidates; ++currentValue)
    {
        values[numValues++] = candidates[currentValue];
    }
  }
  
  if (numValues != 0)
    return values[0];

  return Set64(0, 0);
}

simulated function BeginPlay()
{
  local string Program;
  
  Super.BeginPlay();
  
  Program = "2411750314455530";
  ResetVm(Set64(0, 51571418), Set64(0, 0), Set64(0, 0), Program);
  DisplayText = "Part 1: " $ Run();
  
  ResetVM(RestoreRegisterValue(Program), Set64(0, 0), Set64(0, 0), Program);
  DisplayText = DisplayText $ " " $ "Part 2: " $ Run();
}

simulated event RenderTexture(ScriptedTexture Tex)
{
  if(LastDrawTime == 0)
      Position = Tex.USize;
  else
      Position -= (Level.TimeSeconds-LastDrawTime) * PixelsPerSecond;

  if(Position < -ScrollWidth)
      Position = Tex.USize;

  LastDrawTime = Level.TimeSeconds;
  
  Tex.DrawColoredText(Position, YPos, Caps(DisplayText), Font, FontColor);
}
