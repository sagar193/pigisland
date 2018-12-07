{ pkgs ? import <nixpkgs> {} }:
pkgs.mkShell rec {
  buildInputs = with pkgs; [ clang-tools ninja cmake SDL2 SDL2_image gtest pkgconfig ];
}
