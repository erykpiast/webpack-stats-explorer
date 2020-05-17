const API_URL = 'https://dev.to/api/articles';

function extractJson(response) {
    return response.json();
}

export function fetchFullArticles() {
    return fetch(`${API_URL}?per_page=5`)
        .then(extractJson)
        .then((articles) => {
            const fullArticles = articles.map((article) =>
                fetch(`${API_URL}/${article.id}`).then(extractJson)
            );

            return Promise.all(fullArticles);
        });
}