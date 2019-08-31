export default async function (a, b = 1, ...c) {
  const [c1, c2] = await Promise.all(c);
  return [a, b, c1, ...c2];
}