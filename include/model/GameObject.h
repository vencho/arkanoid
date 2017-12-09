#ifndef GAME_OBJECT_H_DEFINED
#define GAME_OBJECT_H_DEFINED
class GameObject {
 private:
  int id;
  static int next_id_to_assign;

 public:
  int getId() const;
  void assignNewId();
  GameObject();
};
#endif
