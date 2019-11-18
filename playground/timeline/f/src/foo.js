export default function foo() {
  return Array.from({
    length: 21
  }, (_, index) => `foo${index}`);
}