function d() {
    const d = 0;
    const f = [
        "so it won't be present",
        "in the final bundle"
    ];
    if (d === 1) {
        const e = [
            "It's",
            "quite a lot",
            "of code",
            "that the minimzer",
            "should cut off",
            ...f
        ].map((value, index) => [index, value]);
        const ee = new Map(e);
    }
    return 1;
}

export default async function (a, b = d(), ...c) {
    return [a, b, ...await Promise.all(c)];
}