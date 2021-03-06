
//============================================================================================
// Do not edit. This file generated by /home/ubuntu/DDLParser/ddlt/ddlt on 24 April 2012 06:20
//============================================================================================

#include "mariner.h"

#include "JsonWriteScope.h"


//================================================================================
// Select Weapon
//================================================================================

void Weapon::Set ( uint32_t value )
{
  switch ( value ) // Check for a valid value.
  {
    case kFist:
    case kChainsaw:
    case kPistol:
    case kShotgun:
    case kChaingun:
    case kRocketLauncher:
    case kPlasmaGun:
    case kBFG9000:
      m_Value = value;
      break;
  }
}

const char* Weapon::GetName ( uint32_t value )
{
  switch ( value ) // Check for a valid value.
  {
    case kFist:
      return "kFist";
      break;
    case kChainsaw:
      return "kChainsaw";
      break;
    case kPistol:
      return "kPistol";
      break;
    case kShotgun:
      return "kShotgun";
      break;
    case kChaingun:
      return "kChaingun";
      break;
    case kRocketLauncher:
      return "kRocketLauncher";
      break;
    case kPlasmaGun:
      return "kPlasmaGun";
      break;
    case kBFG9000:
      return "kBFG9000";
      break;
    default:
      return "unknown";
  }
}

bool Weapon::WriteJson ( JsonWriteScope* parent_scope, const char* name )
{
  parent_scope->WriteString ( GetName ( m_Value ), name );
  return true;
}


//================================================================================
// Struct Position
//================================================================================

bool Position::Init()
{
  bool ok = true;
  m_X = 0.000000f;
  m_Y = 0.000000f;
  m_Angle = 0.000000f;
  return ok;
}

bool Position::WriteJson ( char*& output, size_t& size, const char* name )
{
  JsonWriteScope  json ( output, size );
  return WriteJson ( &json, name );
}

bool Position::WriteJson ( JsonWriteScope* parent_scope, const char* name )
{
  bool ok = true;
  JsonWriteScopeObject json ( parent_scope, name );
  json.WriteFloat ( m_X, "X" );
  json.WriteFloat ( m_Y, "Y" );
  json.WriteFloat ( m_Angle, "Angle" );
  return ok;
}

//================================================================================
// Struct Mariner
//================================================================================

bool Mariner::Init()
{
  bool ok = true;
  m_Health = 100UL;
  ok = ok && m_Weapon.Init();
  m_Weapon.Set ( Weapon::kPistol ); // kPistol
  strncpy ( m_Name, "Mariner", sizeof ( m_Name ) );
  m_Name[ sizeof ( m_Name ) - 1 ] = 0;
  ok = ok && m_Position.Init();
  m_Position.SetX ( 100.000000f );
  m_Position.SetY ( 120.000000f );
  m_Timestamp[ 0 ] = 0;
  return ok;
}

bool Mariner::WriteJson ( char*& output, size_t& size, const char* name )
{
  JsonWriteScope  json ( output, size );
  return WriteJson ( &json, name );
}

bool Mariner::WriteJson ( JsonWriteScope* parent_scope, const char* name )
{
  bool ok = true;
  JsonWriteScopeObject json ( parent_scope, name );
  json.WriteUInt ( m_Health, "Health" );
  ok = ok && m_Weapon.WriteJson ( &json, "Weapon" );
  json.WriteString ( m_Name, "Name" );
  ok = ok && m_Position.WriteJson ( &json, "Position" );
  json.WriteString ( m_Timestamp, "Timestamp" );
  return ok;
}
