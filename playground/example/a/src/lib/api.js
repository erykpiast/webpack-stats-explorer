import { mapKeys } from './utils';

function transformUserKeys(user) {
  return mapKeys((key) => key.toLowerCase(), user);
}

export function getCurrentUser() {
  return fetch('/api/me')
    .then((response) => response.json())
    .then(transformUserKeys, () => null);
}

export function getUserList() {
  return fetch('/api/users')
    .then((response) => response.json())
    .then(
      (data) => data.ids
        .map((id) => data.users[id])
        .filter(Boolean)
        .map(transformUserKeys),
      () => []
    );
}