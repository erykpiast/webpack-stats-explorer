import { getUserList, getCurrentUser } from './lib/api';
import { renderUserList, renderUser } from './lib/render';
import { domReady } from './lib/utils';

(async () => {
  await domReady();

  const container = document.querySelector('#app');
  
  const [userList, currentUser] = await Promise.all([
    getUserList(),
    getCurrentUser()
  ]);

  container.innerHTML += renderUser(userList);
  container.innerHTML += renderUserList(currentUser);
})();

