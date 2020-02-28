function appendChild(parent) {
    return (child) => {
        if (!child) {
            return;
        }

        let childNode = typeof child === 'string' ?
            document.createTextNode(child) :
            child;

        parent.appendChild(childNode);
    };
}

export function createElement(tagName, props, ...children) {
    const element = document.createElement(tagName);

    Object.assign(element, props);

    const appendToElement = appendChild(element);
    children.flat().forEach(appendToElement);

    return element;
}

export function safeHtml(markup) {
    const template = document.createElement('template');
    template.innerHTML = markup;
    return template.content;
}

export default {
    createElement,
    safeHtml
};