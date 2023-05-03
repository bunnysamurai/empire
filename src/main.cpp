
struct State;

static State game_state;

static void game_init() {
  /* At the start of the game:
   *      1. Purchase
   *      2. Place
   */
  purchase_phase(game_state);
  placement_phase(game_state);
}

static void game_loop() {
  /* The game consists of phases for each player.
   * We're doing this real old school, IGOYOUGO.
   *  Then, on every player's turn:
   * 1. Move
   * 2. Attack
   * 3. Score update
   */
  set_initial_player(game_state);
  while (!end_state(game_state)) {
    move_phase(game_state);
    attack_phase(game_state);
    update_score(game_state);
    set_next_active_player(game_state);
  }
}

int main() {}