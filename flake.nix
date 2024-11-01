{
  description = "Game of 24";

  inputs = {
    nixpkgs.url = "github:nixos/nixpkgs?ref=nixos-unstable";
    treefmt-nix.url = "github:numtide/treefmt-nix";
  };

  outputs =
    {
      self,
      nixpkgs,
      treefmt-nix,
      ...
    }:
    let
      name = "gameof24";
      systems = [ "x86_64-linux" ];
      eachSystem =
        f:
        let
          forAllSystems = nixpkgs.lib.genAttrs systems;
        in
        forAllSystems (
          system:
          f {
            inherit system;
            pkgs = import nixpkgs { inherit system; };
          }
        );
    in
    {
      formatter = eachSystem (
        {
          pkgs,
          system,
        }:
        let
          treefmtEval = treefmt-nix.lib.evalModule pkgs ./treefmt.nix;
        in
        treefmtEval.config.build.wrapper
      );

      packages = eachSystem (
        {
          pkgs,
          system,
        }:
        {
          default = pkgs.stdenv.mkDerivation rec {
            inherit name;
            src = ./.;
            makefile = ./Makefile;
            buildInputs = with pkgs; [ gcc ];
            makeFlags = [ "build" ];
            installPhase = ''
              mkdir -p $out/bin
              ls -la
              cp bin/${name} $out/bin/${name}
            '';
          };
        }
      );

      apps = eachSystem (
        {
          pkgs,
          system,
        }:
        {
          default = {
            type = "app";
            program = "${self.packages.${system}.default}/bin/${name}";
          };
        }
      );

      devShells = eachSystem (
        { pkgs, system }:
        {
          default = pkgs.mkShell {
            packages = with pkgs; [
              gcc
              valgrind
              bc
            ];
          };
        }
      );
    };
}
