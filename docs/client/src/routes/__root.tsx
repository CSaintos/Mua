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
    width:"100%",
    minHeight:"100vh",
  }}>
    <Box
    sx={{
      height:"50px"
    }}>
      <Header />
    </Box>
    <Box
    sx={{
      minHeight:"93vh",
      height:"93vh"
    }}>
      <Outlet />
    </Box>
  </Box>
}
