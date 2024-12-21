const PART = 2;

const KEYPAD_NUMBERS = [
  ['7', '8', '9'],
  ['4', '5', '6'],
  ['1', '2', '3'],
  [null, '0', 'A'],
];

const KEYPAD_DIRECTIONAL = [
  [null, '^', 'A'],
  ['<', 'v', '>'],
];

type Position = { y: number, x: number};
type Keypad = (string|null)[][];

function findKeyPosition(keypad: Keypad, key: string): Position | null {
  for (let y = 0; y < keypad.length; y++) {
    for (let x = 0; x < keypad[y].length; x++) {
      if (keypad[y][x] === key) {
        return { x, y };
      }
    }
  }
  return null;
}

function positionToIndex(keypad: Keypad, pos: Position): number {
  return pos.y * keypad[0].length + pos.x;
}

function getAllShortestPaths(startKey: string, endKey: string, keypad: Keypad): string[] {
  const start = findKeyPosition(keypad, startKey);
  const end = findKeyPosition(keypad, endKey);
  
  if (!start || !end) {
    return [];
  }

  const queue: { position: Position; path: string }[] = [
    { position: start, path: "" },
  ];

  const visited = new Map<number, number>();
  visited.set(positionToIndex(keypad, start), 0);

  const directions = [
    { x: -1, y:  0, val: '<' },
    { x:  1, y:  0, val: '>' },
    { x:  0, y: -1, val: '^' },
    { x:  0, y:  1, val: 'v' },
  ];

  const results: string[] = [];
  let shortestDistance = Infinity;

  while (queue.length > 0) {
    const { position, path } = queue.shift()!;
    const currentDistance = path.length - 1;

    if (currentDistance > shortestDistance) { 
      continue;
    }

    if (position.x === end.x && position.y === end.y) {
      if (currentDistance < shortestDistance) {
        shortestDistance = currentDistance;
        results.length = 0;
      }
      results.push(path + "A");
      continue;
    }

    for (const direction of directions) {
      const newX = position.x + direction.x;
      const newY = position.y + direction.y;

      if (newX >= 0 && newX < keypad[0].length && newY >= 0 && newY < keypad.length && keypad[newY][newX] !== null) {
        const newPos = { x: newX, y: newY };
        const posKey = positionToIndex(keypad, newPos);
        const newDistance = currentDistance + 1;

        if (!visited.has(posKey) || newDistance <= visited.get(posKey)!) {
          visited.set(posKey, newDistance);
          queue.push({
            position: newPos,
            path: path + direction.val,
          });
        }
      }
    }
  }

  return results;
}

function transformKeySequence(code: string, keypad: Keypad, layer: number, cache: Record<string, number> = {}): number {
  const key = `${code},${layer}`;
  if (cache[key] !== undefined) {
    return cache[key];
  }

  let currentKey = 'A';
  let totalLength = 0;
  
  for (const nextKey of code) {
      const paths = getAllShortestPaths(currentKey, nextKey, keypad);
      if (layer === 0) {
          totalLength += paths[0].length;
      } else {
          totalLength += Math.min(
              ...paths.map(path => transformKeySequence(path, KEYPAD_DIRECTIONAL, layer - 1, cache))
          );
      }
      currentKey = nextKey;
  }

  cache[key] = totalLength;
  return totalLength;
}

const data = [
  "129A",
  "176A",
  "985A",
  "170A",
  "528A"
];

let totalCost = 0;
data.forEach(code => {
  totalCost += parseInt(code) * transformKeySequence(code, KEYPAD_NUMBERS, PART === 1 ? 2 : 25);
});

console.log(totalCost);