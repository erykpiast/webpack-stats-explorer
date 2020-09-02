import React, { useState, useEffect, useCallback } from "react";

const API_ROOT = "https://registry.npmjs.com/-/v1/search";

export default function App() {
  const [phrase, setPhrase] = useState("");
  const [results, setResults] = useState([]);
  const [loading, setLoading] = useState(false);

  const fetchResults = useCallback(
    async (signal) => {
      if (!phrase) {
        return;
      }

      setLoading(true);

      const response = await fetch(
        `${API_ROOT}?text=${encodeURIComponent(phrase)}`,
        {
          method: "GET",
          signal,
        }
      );
      const { objects } = await response.json();

      setResults(objects);
      setLoading(false);
    },
    [phrase]
  );

  useEffect(() => {
    const controller = new AbortController();

    fetchResults(controller.signal);

    return () => {
      controller.abort();
    };
  }, [phrase]);

  return (
    <section>
      <header>
        <input
          type="text"
          value={phrase}
          onInput={(e) => setPhrase(e.target.value)}
          placeholder="Search packages"
        />
      </header>
      {loading && <span>Loading...</span>}
      <ul>
        {results.map((result) => (
          <li key={result.package.name}>{result.package.name}</li>
        ))}
      </ul>
    </section>
  );
}
