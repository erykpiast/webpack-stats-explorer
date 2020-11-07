export default async function (a, { b } = {}, ...c) {
  return [await a, b, c];
}