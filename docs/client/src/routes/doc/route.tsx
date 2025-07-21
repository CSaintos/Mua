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

export const Route = createFileRoute('/doc')({
  component: RouteComponent,
})

function SidebarButton({children, path}) {
  const navigate = useNavigate()
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
    color:"white"
  }}>
    {children}
  </ListItemButton>
}

function RouteComponent() {
  return <Box
  sx={{
    boxSizing:"border-box",
    display:"grid",
    gridTemplateRows:"1fr",
    gridTemplateColumns:"1fr 4fr",
    height:"100%",
  }}>
    <Box
    sx={{
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
    <Box>
      <Outlet />
    </Box>
    <title>Docs</title>
  </Box>
} 
