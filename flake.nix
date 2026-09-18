{
  description = "C development environment with Raylib and CMake";

  inputs = {
    nixpkgs.url = "github:nixos/nixpkgs/nixos-unstable";
  };

  outputs = { self, nixpkgs }:
    let
      system = "x86_64-linux";
      pkgs = nixpkgs.legacyPackages.${system};
    in
    {
      devShells.${system}.default = pkgs.mkShell {
        buildInputs = with pkgs; [
          # Compilers & Tooling
          gcc
          clang-tools # Includes clangd LSP
          cmake
          ninja
          bear        # Generates compile_commands.json for clangd
          just

          # Libraries & Graphics Dependencies
          raylib
          xorg.libX11
          xorg.libX11.dev
          xorg.libXcursor
          xorg.libXrandr
          xorg.libXinerama
          xorg.libXi
          libGL
        ];

        shellHook = ''
          echo "Raylib + CMake C dev environment loaded."

          # Helper command to configure CMake with Bear for clangd support
          alias gen-compile-cmds="cmake -B build -G Ninja -DCMAKE_EXPORT_COMPILE_COMMANDS=ON && bear -- cmake --build build"
        '';
      };
    };
}
