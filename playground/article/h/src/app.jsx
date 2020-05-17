import { h } from 'preact';
import { useState, useEffect } from 'preact/hooks';

import styles from './app.css';

import { fetchFullArticles } from './api';
import Article from './article';

export default function App() {
    const [articles, setArticles] = useState([]);

    useEffect(() => {
        fetchFullArticles().then(setArticles);
    });

    return <section className={styles.root}>
        <header>
            <h1 className={styles.title}>Latest dev.to articles</h1>
        </header>
        {articles.length
            ? articles.map((article) => <Article {...article} />)
            : <progress className={styles.loader}></progress>}
    </section>
}