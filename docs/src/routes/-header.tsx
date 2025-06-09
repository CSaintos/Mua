import {
  AppBar,
  Toolbar,
  Typography
} from '@mui/material'

export function Header () {
  return <AppBar position='fixed'>
    <Toolbar variant='dense'>
      <Typography
      color='textPrimary'
      variant='h6'
      >
        Mua
      </Typography>
    </Toolbar>
  </AppBar>
}
