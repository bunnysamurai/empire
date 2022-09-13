#if !defined(MAP_HPP)
#define MAP_HPP

#include <array>
#include <cstddef>
#include <cstdint>

using map_dim_t = size_t;
enum struct TileType : uint8_t { OCEAN, COAST, GRASSLAND, MOUNTAIN };
enum struct TileState : uint8_t { OKAY, RUINED, ON_FIRE };
struct Tile {
  TileType type : 2;
  TileState state : 2;
};

template <map_dim_t Width, map_dim_t Height> struct MapParams {
  static constexpr map_dim_t width{Width};
  static constexpr map_dim_t height{Height};
};

using SmallMap = MapParams<64, 64>;
using LargeMap = MapParams<128, 128>;

template <class Parameters> struct Map {
  static constexpr auto width{Parameters::width};
  static constexpr auto height{Parameters::height};
  static std::array<Tile, Parameters::width * Parameters::height> map_;
};

template <class Parameters> constexpr void init() noexcept {
  // TODO stub, just makes an ocean map
  for (size_t ii = 0; ii < Map<Parameters>::map_.size(); ++ii) {
    Map<Parameters>::map_[ii] = Tile{TileType::OCEAN, TileState::OKAY};
  }
}
template <class Parameters>
[[nodiscard]] constexpr Tile &tile(map_dim_t x, map_dim_t y) noexcept {
  return Map<Parameters>::map_[y * Map<Parameters>::width + x];
}
template <class Parameters>
[[nodiscard]] constexpr const Tile &const_tile(map_dim_t x,
                                               map_dim_t y) noexcept {
  return tile<Parameters>(x, y);
}

#endif