import { 
  createFileRoute
} from '@tanstack/react-router'
import {
  Box,
  Typography,
  Button,
  List,
  ListItem,
  ListSubheader
} from '@mui/material'
import {
  useTheme
} from '@mui/material/styles'
import {
  CodeHl
} from "../../Components.tsx"
import type {
  Props
} from "../../Types.tsx"

export const Route = createFileRoute('/doc/')({
  component: RouteComponent,
})

function MListItem({children}: Props) {
  return <ListItem
  sx={{
    display:"list-item",
    ml:"1rem",
    mb:"0.5rem"
  }}>
    {children}
  </ListItem>
}

function RouteComponent() {
  const theme = useTheme()

  return <Box
  sx={{
    color:theme.palette.text.primary,
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
    src={'/repl_demo.gif'}
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
      <MListItem>
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
      </MListItem>
      <MListItem>
        Extract Mua 7zip archive.
        <List
        component="ul"
        sx={{
          listStyleType:"disc"
        }}>
          <MListItem>
            For MacOS: Upon extracting, the file permissions are readonly. Use <CodeHl>chmod 755 *</CodeHl> inside the mua-macos directory to enable permissions.
          </MListItem>
        </List>
      </MListItem>
      <MListItem>
        Install/Place Mua anywhere you'd like on your computer,
      </MListItem>
      <MListItem>
        Add Mua app to system or shell environment path.
      </MListItem>
    </List>
    <Typography
    variant="h5"
    my="1rem"
    sx={{
      fontWeight:"bold"
    }}>
      Using Mua
    </Typography>
    <Typography paragraph>
      In your shell: <CodeHl>./muac -h</CodeHl> for how to use mua.
    </Typography>
    <Typography
    variant="h6"
    my="1rem"
    sx={{
      fontWeight:"bold"
    }}>
      Mua's two modes:
    </Typography>
    <List
    component="ul"
    sx={{
      listStyleType:"disc"
    }}
    subheader={
      <ListSubheader
      sx={{
        backgroundColor:"transparent",
        color:theme.palette.text.primary,
        fontWeight:"bold"
      }}>
        Repl Mode
      </ListSubheader>
    }>
      <MListItem>
        Start repl mode with: <CodeHl>./muac</CodeHl>
      </MListItem>
      <MListItem>
        End repl mode: <CodeHl>exit[];</CodeHl> on an empty line.
      </MListItem>
    </List>
    <List
    component="ul"
    sx={{
      listStyleType:"disc"
    }}
    subheader={
      <ListSubheader
      sx={{
        backgroundColor:"transparent",
        color:theme.palette.text.primary,
        fontWeight:"bold"
      }}>
        File Mode
      </ListSubheader>
    }>
      <MListItem>
        Evaluate mua file: <CodeHl>./muac &lt;path-to-file&gt;.mua [-o &lt;output-file-path&gt;.muar]</CodeHl>
        <List
        component="ul"
        sx={{
          listStyleType:"square",
          p:"0"
        }}>
          <MListItem>
            Brackets mean optional argument
          </MListItem>
        </List>
      </MListItem>
      <MListItem>
        Ex:
       <List
        component="ul"
        sx={{
          listStyleType:"square",
          p:"0"
        }}>
          <MListItem>
            <CodeHl>./muac ./hello_world.mua</CodeHl>
          </MListItem>
          <MListItem>
            <CodeHl>./muac ./hello_world.mua -o ./hello_world.muar</CodeHl>
          </MListItem>
        </List> 
      </MListItem>
    </List>
  </Box>
}
