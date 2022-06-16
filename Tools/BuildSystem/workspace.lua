workspace 'HydraEngine'
  location '../../'

  configurations { 
    'Debug', 
    'Release',
    'Distribution'
  }

  platforms {
    'x64'
  }

  filter 'platforms:x64'
    architecture 'x64'