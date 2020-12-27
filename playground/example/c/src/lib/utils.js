export function formatDate(date) {
  const year = String(date.getFullYear());
  let month = String(date.getMonth() + 1);
  let day = String(date.getDate());

  if (month.length < 2) {
    month = '0' + month;
  }
        
  if (day.length < 2) {
    day = '0' + day;
  }

  return [year, month, day].join('-');
}

export function mapKeys(mapper, object) {
  const entries = Object.entries(object);
  const mappedEntries = entries.map(([key, value]) => [mapper(key), value]);
  return Object.fromEntries(mappedEntries);
}

export function domReady() {
  return new Promise((resolve) => {
    if (document.readyState === 'complete') {
      resolve();
    } else {
      document.addEventListener('DOMContentLoaded', resolve);
    }
  });
}

export async function fetchJson(path) {
  try {
    const response = await fetch(path);
    const data = await response.json();

    return data;
  } catch {
    return null;
  }
}