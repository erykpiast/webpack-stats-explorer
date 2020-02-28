import view from './view';
import {
    fetchFullArticles
} from './api';

const initialView = view({ articles: [] });

document.body.appendChild(initialView);

fetchFullArticles().then((articles) => {
    const newView = view({
        articles
    });
    document.body.replaceChild(newView, initialView);
});