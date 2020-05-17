import { h } from 'preact';

import styles from './article.css';

const renderTags = (tags) => tags
    .split(',')
    .map((tag) => tag.trim())
    .filter((tag) => tag.length > 0)
    .map((tag) => <li className={styles.tag}>{tag}</li>);

export default function Article({ body_html, title, tag_list }) {
    return <article className={styles.root}>
        <header>
            <h2 className={styles.title}>{title}</h2>
            <nav className={styles.tagsContainer}>
                <ul className={styles.tags}>
                    {renderTags(tag_list)}
                </ul>
            </nav>
        </header>
        <div className={styles.content} dangerouslySetInnerHTML={{__html: body_html}} />
    </article>;
}
