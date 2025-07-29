import { StrictMode } from 'react'
import { createRoot } from 'react-dom/client'
import { 
  RouterProvider,
  createRouter
} from '@tanstack/react-router'
import { routeTree } from './routeTree.gen'
import './index.css'
import {
  ThemeProvider,
  createTheme
} from '@mui/material/styles'

const router = createRouter({ 
  routeTree,
  basepath: "/Mua/"
})

declare module '@tanstack/react-router' {
  interface Register {
    router: typeof router
  }
}

const theme = createTheme({
  palette: {
    mode: "dark",
    background: {
      terminal: "#251510",
      output: "#152515"
    }
  }
})

declare module '@mui/material/styles' {
  interface TypeBackground {
    terminal: string;
    output: string;
  }
}

createRoot(document.getElementById('root')!).render(
  <StrictMode>
    <ThemeProvider theme={theme}>
      <RouterProvider router={router} />
    </ThemeProvider>
  </StrictMode>,
)
