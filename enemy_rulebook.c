#include "enemy_rulebook.h"
#include "enemy.h"
#include "list.h"
#include "colors.h"
#include "player.h"
#include "map.h"
#include "main.h"
#include "gui.h"
#include "queue.h"
#include <limits.h>
#include <stdio.h>

static enemy_template_t rulebook[100];
int book_length = 0;
int called = 0;

int hag = 0;
int fake_hag = 0;
int snek = 0;

void generate_enemies(){
	called = 1;

	/* rat */
	rulebook[book_length].name = "rat";
	rulebook[book_length].pic = 'r'|A_BOLD| COLORS_RED;
	rulebook[book_length].base_hp = 30;
	rulebook[book_length].base_sight_range = 10;
	rulebook[book_length].base_exp = 10;
	rulebook[book_length].base_strength = 5;
	book_length++;

	/* kobold */
	rulebook[book_length].name = "kobold";
	rulebook[book_length].pic = 'k'|A_BOLD| COLORS_RED;
	rulebook[book_length].base_hp = 50;
	rulebook[book_length].base_sight_range = 15;
	rulebook[book_length].base_strength = 10;
	rulebook[book_length].base_exp = 15;
	book_length++;

	/* goblin */
	rulebook[book_length].name = "goblin";
	rulebook[book_length].pic = 'g'|A_BOLD| COLORS_RED;
	rulebook[book_length].base_hp = 50;
	rulebook[book_length].base_sight_range = 15;
	rulebook[book_length].base_strength = 15;
	rulebook[book_length].base_exp = 15;
	book_length++;

	/* snake */
	rulebook[book_length].name = "snek";
	rulebook[book_length].pic = 's'|A_BOLD| COLORS_RED;
	rulebook[book_length].base_hp = 50;
	rulebook[book_length].base_sight_range = 15;
	rulebook[book_length].base_strength = 15;
	rulebook[book_length].base_exp = 15;
    snek = book_length;
	book_length++;

	/* slime */
	rulebook[book_length].name = "slime";
	rulebook[book_length].pic = 'm'|A_BOLD| COLORS_RED;
	rulebook[book_length].base_hp = 75;
	rulebook[book_length].base_sight_range = 15;
	rulebook[book_length].base_strength = 7;
	rulebook[book_length].base_exp = 20;
	book_length++;

	/* orc */
	rulebook[book_length].name = "orc";
	rulebook[book_length].pic = 'o'|A_BOLD| COLORS_RED;
	rulebook[book_length].base_hp = 75;
	rulebook[book_length].base_sight_range = 15;
	rulebook[book_length].base_strength = 15;
	rulebook[book_length].base_exp = 20;
	book_length++;

	/* wolf */
	rulebook[book_length].name = "wolf";
	rulebook[book_length].pic = 'w'|A_BOLD| COLORS_RED;
	rulebook[book_length].base_hp = 50;
	rulebook[book_length].base_sight_range = 15;
	rulebook[book_length].base_strength = 30;
	rulebook[book_length].base_exp = 30;
	book_length++;

	/* imp */
	rulebook[book_length].name = "imp";
	rulebook[book_length].pic = 'i'|A_BOLD| COLORS_RED;
	rulebook[book_length].base_hp = 75;
	rulebook[book_length].base_sight_range = 15;
	rulebook[book_length].base_strength = 30;
	rulebook[book_length].base_exp = 35;
	book_length++;

	/* griffin */
	rulebook[book_length].name = "griffin";
	rulebook[book_length].pic = 'G'|A_BOLD| COLORS_RED;
	rulebook[book_length].base_hp = 100;
	rulebook[book_length].base_sight_range = 20;
	rulebook[book_length].base_strength = 30;
	rulebook[book_length].base_exp = 40;
	book_length++;

	/* grue */
	rulebook[book_length].name = "grue";
	rulebook[book_length].pic = 'U'|A_BOLD| COLORS_RED;
	rulebook[book_length].base_hp = 60;
	rulebook[book_length].base_sight_range = 20;
	rulebook[book_length].base_strength = 50;
	rulebook[book_length].base_exp = 40;
	book_length++;

	/* fake hag */
	rulebook[book_length].name = "Hag";
	rulebook[book_length].pic = 'H'|A_BOLD| COLORS_RED;
	rulebook[book_length].base_hp = 1;
	rulebook[book_length].base_sight_range = 0;
	rulebook[book_length].base_strength = 50;
	rulebook[book_length].base_exp = 50;
    fake_hag = book_length;
	book_length++;

	/* hag */
	rulebook[book_length].name = "Hag";
	rulebook[book_length].pic = 'H'|A_BOLD| COLORS_RED;
	rulebook[book_length].base_hp = 30;
	rulebook[book_length].base_sight_range = 0;
	rulebook[book_length].base_strength = 60;
	rulebook[book_length].base_exp = 70;
    hag = book_length;
	book_length++;
	
	

}
enemy_template_t * get_rulebook(){
	if(!called){
		generate_enemies();
	}
	return rulebook;
}

int enemy_index_hag() {
    return hag;
}

int enemy_index_fake_hag() {
    return fake_hag;
}


int enemy_index_snek() {
    return snek;
}

queue_t *pathfind(enemy_t *e, int y, int x, int *xn, int *yn){
	int range = e->sight_range*2-1;
	queue_t *q = queue_create();
	int prevC[range][range];
	int prevR[range][range];
	int sX, sY, m, n;
	int ePos = range/2;

	for(m=0; m<range; m++){
		for(n=0; n<range; n++){
			prevC[m][n] = -1;
			prevR[m][n] = -1;
		}
	}

	sX = ePos + (x - e->x);
	sY = ePos + (y - e->y);
	queue_push(q, 0, sX, sY, -1, -1);
	
	while(!queue_empty(q)){
		tile_t *t = queue_top(q);
		int currC = t->x;
		int currR = t->y;
		int tCost = t->cost;
		if(prevR[currR][currC] != -1){
			q = queue_pop(q);
			continue;
		}
		prevC[currR][currC] = t->xPrev;
		prevR[currR][currC] = t->yPrev;
		q = queue_pop(q);

		if(currC == ePos && currR == ePos){
			if(map_get(e->y - (currR - prevR[currR][currC]), e->x - (currC - prevC[currR][currC])) == '#'){
				continue;
			}
			*xn -= (currC - prevC[currR][currC]);
			*yn -= (currR - prevR[currR][currC]);
			return q;
		}
			
		if((currR-1 >= 0 && currC-1 >= 0) && (prevC[currR-1][currC-1] == -1) && map_get(e->y - (ePos - (currR-1)), e->x - (ePos - (currC-1))) == '.'){
			if(tCost < range)
				queue_push(q, tCost+1, currC-1, currR-1, currC, currR);
		}
		if((currR-1 >= 0 && currC+1 < range) && (prevC[currR-1][currC+1] == -1) && map_get(e->y - (ePos - (currR-1)), e->x - (ePos - (currC+1))) == '.'){
			if(tCost < range)
				queue_push(q, tCost+1, currC+1, currR-1, currC, currR);
		}
		if((currR+1 < range && currC-1 >= 0) && (prevC[currR+1][currC-1] == -1) && map_get(e->y - (ePos - (currR+1)), e->x - (ePos - (currC-1))) == '.'){
			if(tCost < range)
				queue_push(q, tCost+1, currC-1, currR+1, currC, currR);
		}
		if((currR+1 < range && currC+1 < range) && (prevC[currR+1][currC+1] == -1) && map_get(e->y - (ePos - (currR+1)), e->x - (ePos - (currC+1))) == '.'){
			if(tCost < range)
				queue_push(q, tCost+1, currC+1, currR+1, currC, currR);
		}
		if((currR-1 >= 0) && (prevC[currR-1][currC] == -1) && map_get(e->y - (ePos - (currR-1)), e->x - (ePos - currC)) == '.'){
			if(tCost < range)
				queue_push(q, tCost+1, currC, currR-1, currC, currR);
		}
		if((currC-1 >= 0) && (prevC[currR][currC-1] == -1) && map_get(e->y - (ePos - currR), e->x - (ePos - (currC-1))) == '.'){
			if(tCost < range)
				queue_push(q, tCost+1, currC-1, currR, currC, currR);
		}
		if((currR+1 < range) && (prevC[currR+1][currC] == -1) && map_get(e->y - (ePos - (currR+1)), e->x - (ePos - currC)) == '.'){
			if(tCost < range)
				queue_push(q, tCost+1, currC, currR+1, currC, currR);
		}
		if((currC+1 < range) && (prevC[currR][currC+1] == -1) && map_get(e->y - (ePos - currR), e->x - (ePos - (currC+1))) == '.'){
			if(tCost < range)
				queue_push(q, tCost+1, currC+1, currR, currC, currR);
		}
	}
	return q;
}

void enemy_take_turn(enemy_t *e, WINDOW *win, int y, int x){
    
    int w, h;
    getmaxyx(win, h, w); /*MACRO, changes w and h */
    int y0 = y - (h/2);
    int x0 = x - (w/2);
    int ey = e->y - y0;
    int ex = e->x - x0;
    int yn = e->y;
    int xn = e->x;
    int ydiff = e->y - y;
    int xdiff = e->x - x;
    
    if (ey >= 0 && ex >= 0 && ey < h && ex < w) {  /* if the enemy is on screen */
         /* TODO attacking */
        int i, j;
        for (i = e->x-1; i <= e->x+1; i++){
            for(j = e->y-1; j <= e->y+1; j++){
                if(i == get_player_x() && j == get_player_y()){
                    player_hurt(e->strength);
                    char msg[80];
                    sprintf(msg, "The %s hurts you for %d life.", rulebook[e->type].name, e->strength);
                    add_action(msg);
                    return;
                }
            }
        }

        if ((e->pic & A_CHARTEXT) == 'H') {
            if (tick % 24 == 0) {
            	enemy_template_t en = get_rulebook()[snek];
                add_action("The old hag summons a dangerous snek!");
                enemy_t *n = enemy_add(0, snek, en.pic, en.base_hp, e->y, e->x+xdiff, en.base_sight_range, en.base_strength, en.base_exp, "dangerous snek");
                map_line(e->y, e->x, n->y, n->x);
            }
        }

        /* movement */
        /* if enemy is in range of the player */
        if(abs(ydiff) < e->sight_range && abs(xdiff) < e->sight_range){
        	/*if(ydiff < 0){
                yn++;
            } else if (ydiff > 0){
                yn--;
            }
            if (xdiff < 0){
                xn++;
            } else if (xdiff > 0){
                xn--;
            }*/

			/*queue_t *q0 = queue_create();
			queue_push(q0, 5, x, y, x, y);
			queue_push(q0, 1, x, y, x, y);
			tile_t *t = queue_top(q0);*/

			queue_t *q = pathfind(e, y, x, &xn, &yn); 

			/*char s[80];
			sprintf(s, "%d %d %d %d\n", e->x, e->y, xn, yn);
			add_action(s);*/

            if(map_get(yn, xn) == '.' && !enemy_at(yn,xn)){
                e->y = yn;
                e->x = xn;
            } else if (map_get(yn, e->x) == '.' && !enemy_at(yn,e->x)){
                e->y = yn;
            } else if (map_get(e->y, xn) == '.' && !enemy_at(e->y,xn)){
                e->x = xn;
            }
			queue_clear(q);
        }
    }
   
}
