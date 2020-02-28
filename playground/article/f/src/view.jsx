import {
    isEmpty,
    map,
    pipe,
    reject,
    split,
    trim
} from 'nanoutils';

import DOM from './dom';
import styles from './view.css';

const renderTags = pipe(
    split(','),
    map(trim),
    reject(isEmpty),
    map((tag) => <li className={styles.tag}>{tag}</li>)
);

function renderArticle(article) {
    return <article className={styles.article}>
        <header>
            <h2 className={styles.articleTitle}>{article.title}</h2>
            <nav className={styles.tagsContainer}>
                <ul className={styles.tags}>
                    {renderTags(article.tag_list)}
                </ul>
            </nav>
        </header>
        <div className={styles.content}>
            {DOM.safeHtml(article.body_html)}
        </div>
    </article>;
}

export default function View({ articles }) {
    return <section className={styles.root}>
        <header>
            <h1 className={styles.title}>Latest dev.to articles</h1>
        </header>
        {articles.length
            ? articles.map(renderArticle)
            : <progress className={styles.loader}></progress>}
    </section>
}