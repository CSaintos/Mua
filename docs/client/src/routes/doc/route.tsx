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

function RouteComponent() {
  const navigate = useNavigate()
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
        <ListItemButton
        onMouseOver={(event) => {
          event.target.style.backgroundColor = "#555";
        }}
        onMouseOut={(event) => {
          event.target.style.backgroundColor = "#222";
        }}
        onMouseDown={() => {
          navigate({to:'/doc'})
        }}
        sx={{
          color:"white"
        }}
        >
          Getting Started
        </ListItemButton>
      </List>
    </Box>
    <Box>
      <Outlet />
    </Box>
    <title>Docs</title>
  </Box>
} 
