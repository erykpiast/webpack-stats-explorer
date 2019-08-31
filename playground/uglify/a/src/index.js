function foo(bar) {
    return [bar];
}

export default class Foo {
    constructor(args) {
        foo(args);
    }
}