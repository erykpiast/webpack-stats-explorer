import foo from './foo';

export default class Foo {
    constructor(args) {
        this.x = foo(args);
    }
}