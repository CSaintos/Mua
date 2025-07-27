import { 
  createFileRoute,
  Outlet,
  useNavigate
} from '@tanstack/react-router'
import {
  Box,
  List,
  ListItemButton
} from '@mui/material'
import {
  useTheme
} from '@mui/material/styles'

export const Route = createFileRoute('/doc')({
  component: RouteComponent,
})

function SidebarButton({children, path}) {
  const navigate = useNavigate()
  const theme = useTheme()

  return <ListItemButton
  onMouseOver={(event) => {
    event.target.style.backgroundColor = "#555";
  }}
  onMouseOut={(event) => {
    event.target.style.backgroundColor = "#222";
  }}
  onMouseDown={() => {
    navigate({to:path})
  }}
  sx={{
    color:theme.palette.text.primary
  }}>
    {children}
  </ListItemButton>
}

function RouteComponent() {
  return <Box
  sx={{
    boxSizing:"border-box",
    display:"grid",
    gridTemplateColumns:"1fr 5fr",
    height:"100%",
  }}>
    <Box
    sx={{
      width:"20vw",
      minWidth:"140px",
      maxWidth:"200px",
      borderRight:"1px solid gray"
    }}>
      <List>
        <SidebarButton
        path="/doc">
          Getting Started
        </SidebarButton>
        <SidebarButton
        path="/doc/arithmetic">
          Arithmetic
        </SidebarButton>
      </List>
    </Box>
    <Box
    sx={{
      maxWidth:"80vw",
    }}>
      <Outlet />
    </Box>
    <title>Docs</title>
  </Box>
} 
