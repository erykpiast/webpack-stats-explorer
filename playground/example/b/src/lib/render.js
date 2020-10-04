import { formatDate } from './utils';

export function renderUser(user) {
  if (!user) {
    user = {
      name: 'Unknown User',
      avatar: '/img/default-avatar.png',
      birthday: 0,
      role: 'Unknown'
    };
  }

  const birthday = new Date(user.birthday);
  return `<section>
    <header>
      <img src="${user.avatar}">
      <h2>${user.name}</h2>
    </header>
    <dl>
      <dt>Birthday</dt>
      <dd><time datetime="${birthday.toISOString()}">${formatDate(birthday)}</time></dd>
      <dt>Role</dt>
      <dd>${user.role}</dd>
    </dl>
  </section>`;
}

export function renderUserList(users) {
  if (!users || !users.length) {
    return '<section>No users</section>';
  }

  return `<section>
    <header>Users</header>
    <ul>
      ${users.map(renderUser).join('\n')}
    </ul>
  </section>`;
}