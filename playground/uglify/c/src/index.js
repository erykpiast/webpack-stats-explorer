function fooFooFooFooFooFooFoo(barBarBarBarBarBarBar) {
    return [barBarBarBarBarBarBar];
}

export default class FooFoFooFooFooFooFooFoo {
    constructor(argsArgsArgsArgsArgsArgs) {
        fooFooFooFooFooFooFoo(argsArgsArgsArgsArgsArgs);

        const x = 1 + 2;
        const y = 2 + 1;

        if (x !== y) {
            document.body.firstElementChild.innerHTML = [
                'this',
                'code',
                'should',
                'never',
                'run',
                'nor',
                'appear',
                'in',
                'minified',
                'bundle'
            ].join(' ');
        }
    }
}