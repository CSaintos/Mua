import { 
  createFileRoute
} from '@tanstack/react-router'
import {
  Box,
  Typography,
  Button,
  List,
  ListItem
} from '@mui/material'

export const Route = createFileRoute('/doc/')({
  component: RouteComponent,
})

function RouteComponent() {
  return <Box
  sx={{
    color:"white",
    p:"1rem 2rem",
    display:"flex",
    flexDirection:"column"
  }}>
    <Typography 
    variant="h3" 
    gutterBottom
    sx={{
      fontWeight:"bold"
    }}>
      What is Mua?
    </Typography>
    <Typography paragraph>
      Mua is a &nbsp;
      <span style={{color:"gray"}}>
      (step-by-step, cli-based, arithmetic)
      </span> 
      &nbsp;calculator.
    </Typography>
    <img
    src={'repl_demo.gif'}
    alt="mua_repl_demo"
    style={{
      maxWidth:"50%",
      minWidth:"16rem",
      flexShrink:"2"
    }}
    />

    <Typography 
    variant="h5"
    my="1rem"
    sx={{
      fontWeight:"bold"
    }}
    >
      Getting Started
    </Typography>
    <List
    component="ol"
    sx={{
      listStyleType:"decimal",
    }}
    >
      <ListItem
      sx={{
        display:"list-item",
        ml:"1rem",
        mb:"0.5rem"
      }}
      >
        <Button 
        variant="outlined"
        href="https://github.com/CSaintos/Mua/releases"
        target="_blank"
        sx={{
          width:"10rem",
        }}
        >
          Download Mua
        </Button>
      </ListItem>
      <ListItem
      sx={{
        display:"list-item",
        ml:"1rem",
        mb:"0.5rem"
      }}>
        Extract Mua 7zip archive.
      </ListItem>
    </List>

    <Box
    sx={{
      display:"flex",
      alignItems:"center"
    }}
    >
      1.
      <Button 
      variant="outlined"
      href="https://github.com/CSaintos/Mua/releases"
      target="_blank"
      sx={{
        width:"10rem",
        ml:"1rem"
      }}
      >
        Download Mua
      </Button>
    </Box>
  </Box>
}
