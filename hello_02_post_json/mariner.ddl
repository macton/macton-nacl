select Weapon
{
  kFist,           description( "Bare hands" ),               label( "Fist" );
  kChainsaw,       description( "A la Chainsaw Massacre" ),   label( "Chainsaw" );
  kPistol,         description( "Simple pistol" ),            label( "Pistol" ), default;
  kShotgun,        description( "A single-barrel shotgun" ),  label( "Shotgun" );
  kChaingun,       description( "A machine gun" ),            label( "Chaingun" );
  kRocketLauncher, description( "Portable rocket launcher" ), label( "Rocket launcher" );
  kPlasmaGun,      description( "Plasma gun" ),               label( "Plasma gun" );
  kBFG9000,        description( "*The* BFG 9000" ),           label( "BFG 9000" );
}
struct Position
{
  f32 X,     value( 0 );
  f32 Y,     value( 0 );
  f32 Angle, value( 0 ), description( "The direction the player is looking at ( degrees )" );
}

struct Mariner
{
  u32        Health,   value( 100 ),                  description( "The player's health" );
  Weapon     Weapon,   value( kPistol ),              description( "The player's current weapon" );
  string     Name,     value( "Mariner" ),            description( "The player's name for multiplayer sessions" );
  Position   Position, value( { X = 100, Y = 120 } ), description( "The player's position" );
}
