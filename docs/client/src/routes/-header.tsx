import {
  AppBar,
  ButtonBase,
  Toolbar,
  Typography
} from '@mui/material'
import { useNavigate } from '@tanstack/react-router'

export function Header () {
  const navigate = useNavigate()
  return <AppBar position='fixed'>
    <Toolbar variant='dense'>
      <ButtonBase
      onClick={() => navigate({to: '/'})}
      >
        <Typography
        color='textPrimary'
        variant='h6'
        >
          Mua
        </Typography>
      </ButtonBase>
    </Toolbar>
  </AppBar>
}
