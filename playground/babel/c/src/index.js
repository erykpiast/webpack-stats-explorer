export default function (a, b = 1, ...c) {
  const [c1, c2] = c;
  return [a, b, c1, c2];
}