import { 
  useState, 
  useEffect,
} from 'react';
import type {
  ReactNode
} from 'react'
import { 
  createFileRoute,
} from '@tanstack/react-router'
import {
  InputBase,
  Box,
  Typography,
  useMediaQuery
} from '@mui/material'
import {
  useTheme
} from '@mui/material/styles'
// @ts-expect-error generated wasm glue code
import createModule from "../mua_api.mjs"

export const Route = createFileRoute('/')({
  component: Index
})

function Index() {
  const theme = useTheme()
  const [muaApi, setMuaApi] = useState()
  const [muaCode, setMuaCode] = useState('') 
  const [muaOutput, setMuaOutput] = useState('')
  const isMobile = useMediaQuery('(width < 600px)')
  const rows = isMobile ? window.innerHeight * .44 / 23 - 2 : window.innerHeight * .92 / 23 - 2; //isMobile ? 14 : 28

  useEffect(
    () => {
      // @ts-expect-error Module is part of wasm glue code
      createModule().then((Module) => {
        setMuaApi(() => {return new Module.MuaApi()})
      })
    }, []
  );

  let MuaLayout;

  if (isMobile) {
    MuaLayout = (inputComponent:ReactNode, outputComponent:ReactNode) => {
    return <Box
    sx={{
      boxSizing:"border-box",
      display:"grid",
      gridTemplateColumns:"1fr",
      gridTemplateRows:"1fr 1fr",
      width:"100%",
      height:"100%",
      p:"1rem"
    }}>
      <Box
      sx={{
        boxSizing:"border-box",
        backgroundColor:theme.palette.background.output,
        borderRadius:"3%",
        mb:"0.25rem",
        p:"0.5rem",
        height:"44vh"
      }}>
        {outputComponent}
      </Box>
      <Box
      sx={{
        boxSizing:"border-box",
        backgroundColor:theme.palette.background.terminal,
        borderRadius:"3%",
        mt:"0.25rem",
        p:"0.5rem",
      }}>
        {inputComponent}
      </Box>
    </Box>
    }
  } else {
    MuaLayout = (inputComponent:ReactNode, outputComponent:ReactNode) => {
    return <Box
    sx={{
      boxSizing:"border-box",
      display:"grid",
      gridTemplateColumns:"1fr 1fr",
      gridTemplateRows:"1fr",
      width:"100%",
      height:"100%",
      p:"1rem"
    }}>
      <Box
      sx={{
        boxSizing:"border-box",
        backgroundColor:theme.palette.background.terminal,
        borderRadius:"3%",
        mr:"0.25rem",
        p:"1rem"
      }}>
        {inputComponent}
      </Box>
      <Box
      sx={{
        boxSizing:"border-box",
        backgroundColor:theme.palette.background.output,
        borderRadius:"3%",
        ml:"0.25rem",
        p:"1rem",
        maxHeight:"91vh"
      }}>
        {outputComponent}
      </Box>
    </Box>
    }
  }

  const MuaInput = 
  <InputBase
  fullWidth
  multiline
  minRows={rows}
  maxRows={rows}
  autoFocus={true}
  placeholder='1+1;'
  defaultValue={muaCode}
  onChange={(event) => {
    setMuaCode(event.currentTarget.value)
    // @ts-expect-error calculate is a function of Module
    setMuaOutput(muaApi?.calculate(event.currentTarget.value, false))
  }}
  sx={{
    borderWidth:'0'
  }}
  />

  const MuaOutput = 
  <Typography
  color="textPrimary"
  sx={{
    whiteSpace:"pre-wrap",
    overflow: "auto",
    maxHeight:"100%",
  }}>
    {muaOutput}
  </Typography>

  return MuaLayout(MuaInput, MuaOutput);
}
