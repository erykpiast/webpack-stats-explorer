export default async function (a, b = 1, ...c) {
  return [a, b, ...(await Promise.all(c))];
}
