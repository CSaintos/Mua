import { 
  createRootRoute, 
  Outlet 
} from '@tanstack/react-router'
import { Header } from './-header'
import {
  Stack,
  Box
} from '@mui/material'


export const Route = createRootRoute({
  component: Home
})

function Home() {
  return <>
    <Stack>
      <Box sx={{minHeight:"6.4vh"}}>
        <Header />
      </Box>
      <Box sx={{minHeight:"81vh"}}>
        <Outlet />
      </Box>
    </Stack>
  </>
}
