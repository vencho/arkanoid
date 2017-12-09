#include<model/GameObject.h>
#include<cstdio>
int GameObject::next_id_to_assign = 1;
GameObject::GameObject() {
  assignNewId();
}
int GameObject::getId() const {
  return id;
}
void GameObject::assignNewId() {
 id = next_id_to_assign++;
}
