import { getUserList, getCurrentUser } from './lib/api';
import { renderUserList, renderUser } from './lib/render';
import { domReady } from './lib/utils';

function init() {
  const container = document.querySelector('#app');

  Promise.all([
    getUserList(),
    getCurrentUser()
  ]).then((data) => {
    container.innerHTML += renderUser(data[0]);
    container.innerHTML += renderUserList(data[1]);
  });
}

domReady().then(init);
