import { getUserList, getCurrentUser } from './lib/api';
import { renderUserList, renderUser } from './lib/render';
import { domReady } from './lib/utils';

(async () => {
  await domReady();

  const container = document.querySelector('#app');
  
  const data = await Promise.all([
    getUserList(),
    getCurrentUser()
  ]);

  container.innerHTML += renderUser(data[0]);
  container.innerHTML += renderUserList(data[1]);
})();

