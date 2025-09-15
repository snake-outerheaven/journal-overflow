#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

typedef struct {
  char name[100];
  unsigned short life;
  unsigned short attack;
  unsigned short defense;
  unsigned short speed;
} Player;

typedef struct {
  char name[100];
  unsigned short life;
  unsigned short attack;
  unsigned short defense;
  unsigned short speed;
} Enemy;

Player *createPlayer(char *name, unsigned short attack, unsigned short defense,
                     unsigned short speed) {
  Player *player = malloc(sizeof(Player));
  strcpy(player->name, name);
  player->life = 100;
  player->attack = attack;
  player->defense = defense;
  player->speed = speed;
  return player;
}

Enemy *createEnemy(char *name, unsigned short attack, unsigned short defense,
                   unsigned short speed) {
  Enemy *enemy = malloc(sizeof(Enemy));
  strcpy(enemy->name, name);
  enemy->life = 100;
  enemy->attack = attack;
  enemy->defense = defense;
  enemy->speed = speed;
  return enemy;
}

void PlayerAttack(Player *player, Enemy *enemy) {
  printf("%s ataca %s!\n", player->name, enemy->name);
  enemy->life -= player->attack - enemy->defense;
}

void EnemyAttack(Enemy *enemy, Player *player) {
  printf("%s ataca %s!\n", enemy->name, player->name);
  player->life -= enemy->attack - player->defense;
}

void PrintStatusPlayer(Player *player) {
  printf("%s: %d/%d\n", player->name, player->life, player->attack);
}

void PrintStatusEnemy(Enemy *enemy) {
  printf("%s: %d/%d\n", enemy->name, enemy->life, enemy->attack);
}

void destroyPlayer(Player *player) { free(player); }

void destroyEnemy(Enemy *enemy) { free(enemy); }

void destroyGame(Player *player, Enemy *enemy) {
  printf("%s e %s saem do campo.\n", player->name, enemy->name);
  destroyPlayer(player);
  destroyEnemy(enemy);
}

void PrintStatus(Player *player, Enemy *enemy) {
  PrintStatusPlayer(player);
  PrintStatusEnemy(enemy);
}

int main(void) {
  Player *player = createPlayer("Neo", 10, 5, 10);
  Enemy *enemy = createEnemy("Smith", 8, 3, 8);
  PrintStatus(player, enemy);
  usleep(750 * 1000);
  PlayerAttack(player, enemy);
  usleep(750 * 1000);
  PrintStatus(player, enemy);
  usleep(750 * 1000);
  EnemyAttack(enemy, player);
  usleep(750 * 1000);
  PrintStatus(player, enemy);
  usleep(750 * 1000);
  destroyGame(player, enemy);
  return 0;
}
