import { 
  createRootRoute, 
  Outlet 
} from '@tanstack/react-router'
import { Header } from './-header'
import {
  Box
} from '@mui/material'


export const Route = createRootRoute({
  component: Home
})

function Home() {
  return <Box
  sx={{
    boxSizing:"border-box",
    display:"grid",
    width:"100%",
    height:"100%",
    gridTemplateColumns:"1fr",
    gridTemplateRows:"1fr 15fr"
  }}>
    <Box>
      <Header />
    </Box>
    <Box>
      <Outlet />
    </Box>
  </Box>
}
