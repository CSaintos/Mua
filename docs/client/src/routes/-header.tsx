import {
  AppBar,
  ButtonBase,
  Toolbar,
  Typography,
} from '@mui/material'
import {
  createSvgIcon
} from '@mui/material/utils'
import { useNavigate } from '@tanstack/react-router'

export function Header () {
  const navigate = useNavigate()
  return <AppBar position='fixed'>
    <Toolbar variant='dense'>
      <ButtonBase
      onClick={() => navigate({to: '/'})}
      sx={{
        mr:"1rem"
      }}
      >
        <MuaIcon
        sx={{
          mr:"0.5rem"
        }}
        />
        <Typography
        color='textPrimary'
        variant='h5'
        >
          Mua
        </Typography>
      </ButtonBase>
      <ButtonBase
      onClick={() => navigate({to: '/doc'})}
      >
        <Typography
        color='textPrimary'
        variant='h6'
        >
          Docs
        </Typography>
      </ButtonBase>
    </Toolbar>
  </AppBar>
}
const MuaIcon = createSvgIcon(
<svg width="256px" height="256px" viewBox="0 0 24.00 24.00" xmlns="http://www.w3.org/2000/svg" fill="#000000" stroke="#000000" stroke-width="0.00024000000000000003">
  <g id="SVGRepo_bgCarrier" stroke-width="0" transform="translate(0,0), scale(1)">
    <rect 
    x="0" 
    y="0" 
    width="24.00" 
    height="24.00" 
    rx="12" 
    fill="#ec7ec9" 
    strokewidth="0"
    />
  </g>
  <g id="SVGRepo_tracerCarrier" stroke-linecap="round" stroke-linejoin="round" stroke="#CCCCCC" stroke-width="0.336"/>
  <g id="SVGRepo_iconCarrier">
    <path d="M19 15v1a3.004 3.004 0 0 1-2.94-2.41A5.78 5.78 0 0 1 11.25 16 3.741 3.741 0 0 1 8 14.408V21H7V3h1v7.25C8 14.508 9.854 15 11.25 15A5.05 5.05 0 0 0 16 11.665V3h1v10a2.003 2.003 0 0 0 2 2z"/>
    <path fill="none" d="M0 0h24v24H0z"/>
  </g>
</svg>,
'Mua'
);
