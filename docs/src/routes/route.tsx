import { 
  createFileRoute,
} from '@tanstack/react-router'
import {
  Grid,
} from '@mui/material';

export const Route = createFileRoute('/')({
  component: Index
})

function Index() {
  return <>
    <Grid container columns={2} spacing={1} sx={{padding:'0.5rem', minHeight:'93vh'}}>
      <Grid size={{xs:2, sm:1}} sx={{backgroundColor:'orange'}}>
      </Grid>
      <Grid size={{xs:2, sm:1}} sx={{backgroundColor:'green'}}>
      </Grid>
    </Grid>
  </>
}
