export default function bar() {
  return Array.from({
    length: 21
  }, (_, index) => `bar${index}`);
}