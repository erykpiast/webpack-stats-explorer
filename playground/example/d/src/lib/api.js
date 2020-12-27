import { mapKeys } from './utils';

function transformUserKeys(user) {
  return mapKeys((key) => key.toLowerCase(), user);
}

export async function getCurrentUser() {
  try {
    const response = await fetch('/api/me');
    const data = await response.json();

    return transformUserKeys(data);
  } catch {
    return null;
  }
}

export async function getUserList() {
  const response = await fetch('/api/users');
  const data = await response.json();

  return data.ids
    .map((id) => data.users[id])
    .filter(Boolean)
    .map(transformUserKeys);
}