import { useState, useEffect } from 'react';
import { 
  createFileRoute,
} from '@tanstack/react-router'
import {
  Grid,
  InputBase
} from '@mui/material'
import createModule from "../mua_api.mjs"

export const Route = createFileRoute('/')({
  component: Index
})

function Index() {
  const [muaApi, setMuaApi] = useState()
  const [muaCode, setMuaCode] = useState('') 
  const rows = 28

  useEffect(
    () => {
      createModule().then((Module) => {
        setMuaApi(() => new Module.MuaApi())
      })
    }, []
  );

  return <>
    <Grid container columns={2} spacing={1} sx={{padding:'0.5rem', minHeight:'93vh'}}>
      <Grid 
      size={{xs:2, sm:1}} 
      sx={{
        backgroundColor:'#777',
        padding:'0.5rem',
        borderRadius:'3%',
      }}>
        <InputBase
        fullWidth
        multiline
        minRows={rows}
        maxRows={rows}
        autoFocus={true}
        placeholder='1+1;'
        onChange={(event) => {
          setMuaCode(event.target.value)
        }}
        sx={{
          borderWidth:'0',
        }}
        />
      </Grid>
      <Grid 
      size={{xs:2, sm:1}} 
      sx={{
        backgroundColor:'#999',
        padding:'0.5rem',
        borderRadius:'3%',
        whiteSpace:"pre-wrap"
      }}>
        {muaApi?.calculate(muaCode, false)}
      </Grid>
    </Grid>
  </>
}
