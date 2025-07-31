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
      sx={{
        mr:"1rem",
      }}
      >
        <Typography
        color='textPrimary'
        variant='h6'
        >
          Docs
        </Typography>
      </ButtonBase>
      <ButtonBase
      href="https://github.com/CSaintos/Mua"
      sx={{
        ml:"auto",
      }}
      >
        <GitHubIcon />
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
    strokeWidth="0"
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

const GitHubIcon = createSvgIcon(
<svg 
className="MuiSvgIcon-root MuiSvgIcon-fontSizeSmall css-1pi2lzz" focusable="false" 
aria-hidden="true" 
viewBox="0 0 24 24">
  <path 
  d="M12 1.27a11 11 0 00-3.48 21.46c.55.09.73-.28.73-.55v-1.84c-3.03.64-3.67-1.46-3.67-1.46-.55-1.29-1.28-1.65-1.28-1.65-.92-.65.1-.65.1-.65 1.1 0 1.73 1.1 1.73 1.1.92 1.65 2.57 1.2 3.21.92a2 2 0 01.64-1.47c-2.47-.27-5.04-1.19-5.04-5.5 0-1.1.46-2.1 1.2-2.84a3.76 3.76 0 010-2.93s.91-.28 3.11 1.1c1.8-.49 3.7-.49 5.5 0 2.1-1.38 3.02-1.1 3.02-1.1a3.76 3.76 0 010 2.93c.83.74 1.2 1.74 1.2 2.94 0 4.21-2.57 5.13-5.04 5.4.45.37.82.92.82 2.02v3.03c0 .27.1.64.73.55A11 11 0 0012 1.27" 
  fill="#fff"
  />
</svg>,
'GitHub'
)
