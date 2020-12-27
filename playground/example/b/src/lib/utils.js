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
  const mappedEntries = entries.map((entry) => [mapper(entry[0]), entry[1]]);
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