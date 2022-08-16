# empire
Turned based game.  At compile time?

# Core Design
Let's start simple: Risk.

## Playing Pieces
There is one type of unit: an armyman.

An armyman has the following characteristics:
| Characteristic | Description |
| --- | --- |
| Move | Can move to a single adjacent (8-way) tile |
| Visibility | Can "see" up to 3 (4-way) tiles away |

There is one way to generate more armymans: in a city

## Confrontations
There are two sides to a confrontation: an attacker and a defender.

Here's the maths for resolving a confontation between one attacker and one defender:
``` cpp
P_tie = 1/6 ~= 0.1667; // probability that two dice rolls have the same value
P_diff = 1 - P_tie; // probability that one roll is higher than another

P_D = 0.5 * P_diff + P_tie; // probability that the Defender wins
P_A = 1 - P_D; // probability that the Attacker wins

r = rand(); // some random real number [0,1]

if( r < P_D )
{
	defender_wins();
}
else
{
	attacker_wins();
}
```

## Map Generation
Generate an MxN map of tiles.  "Passable" terrain should tend to group together, and only for a certain portion of the board.  The remaining portion will be "Impassable".

### Generation
How to do this?  Could do a seed fill, could use a 2-D function (with noise added).

Research this, please.

Should be efficient, with a compact representation.

### Tiles
| Name | Passable? | Description |
| --- | --- | --- |
| Grassland | Y | Normal  terrain |
| Ocean | N | Wet terrain |
| Mountain | Y | Difficult terrain |
| City | Y | Producing  terrain |

# Gameplay
This is a turn based game, with phases.  Elements of A & A and TPG2.
1) Order new units
2) Move
3) Attack
4) Place new units

## Order
Gain a fixed amount of resources.

Decide how much to spend.

A few factors dynamically affect the cost of the unit.
| Factor | Description |
| --- | --- |
| Unit Type | What type of unit is this?  The more capable, the more expensive. |
| Logistic | How far away will this unit deploy?  The further from the "center" of the empire, the more expensive. |

Things to buy
* Units
* Advancements (TBD)
* Espionage acts (TBD)

## Move
Units have a move currency.  All movement is 8-way.

Terrain has a movement cost.  If it is Normal, cost 1.  If it is Difficult, costs 2 (or full).  Anything else, can't move.

As units move, they lift a certain amount of the fog-of-war.  Which just reveals if there is an enemy unit or not.

## Attack
Adjacent assaults, only.  For now.


Each unit checks 8-way adajcent.  If it can an enemy, it can attack.

Each unit will have a few characteristics: a range, and a number of attacks.

| Characteristic | Description |
| --- | --- |
| Range | How many 4-way adjacent tiles away an enemy is attackable |
| Attacks | The number of times this unit can attack this phase |

Outcome is resolved via the confrontation rules.  If the Defender loses, it is destroyed.  If the Attacker loses, it is destroyed. Doesn't quite make sense for units with range > 1, but hey this is a start.

## Place New
All new units are placed in Cities.

The elegible Cities a unit can be placed depends upon the number of Logistic Points spent for it.

What is the maths for Logistic Points Cost?
``` cpp
constexpr MapPoint center { empire_center( current_player() ) };

/* Points cost goes up the further from center you are, to a max penality.
     Can just increase the value linearly?  Map penality from [0, MAX_LOGI_COST] to the map's radial size [0, max(map_width, map_height)]
*/
constexpr auto radial_dist { max( get_map_size() ) };
constexpr auto point_cost { map( 0, MAX_LOGI_COST, 0, radial_dist) };

// later
constexpr auto total_cost { point_cost( requested_placement_point() ) + unit_cost( requested_unit() ) };
```



