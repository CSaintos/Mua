import { createFileRoute } from '@tanstack/react-router'
import {
  Box,
  Typography,
  Table,
  TableHead,
  TableCell,
  TableBody,
  TableRow
} from '@mui/material'
import { CodeHl } from '../../MComponents'

export const Route = createFileRoute('/doc/arithmetic')({
  component: RouteComponent,
})

function MTableCell({children}) {
  return <TableCell
  sx={{
    color:"white"
  }}>
    {children}
  </TableCell>
}

function RouteComponent() {
  return <Box
    sx={{
      color:"white",
      p:"1rem 2rem",
      display:"flex",
      flexDirection:"column"
    }}
  >
    <Typography
    variant="h3"
    gutterBottom
    sx={{
      fontWeight:"bold"
    }}>
      Arithmetic Operators
    </Typography>
    <Table 
    aria-label="arithmetic operators"
    >
      <TableHead>
        <TableRow>
        <MTableCell>Operation</MTableCell>
        <MTableCell>Example</MTableCell>
        <MTableCell>Result</MTableCell>
        </TableRow>
      </TableHead>
      <TableBody>
        <TableRow>
          <MTableCell>Addition</MTableCell>
          <MTableCell><CodeHl>1 + 1;</CodeHl></MTableCell>
          <MTableCell><CodeHl>2;</CodeHl></MTableCell>
        </TableRow>
        <TableRow>
          <MTableCell>Subtraction</MTableCell>
          <MTableCell><CodeHl>1-1;</CodeHl></MTableCell>
          <MTableCell><CodeHl>0;</CodeHl></MTableCell>
        </TableRow>
        <TableRow>
          <MTableCell>Multiplication</MTableCell>
          <MTableCell><CodeHl>1 * 1;</CodeHl></MTableCell>
          <MTableCell><CodeHl>1;</CodeHl></MTableCell>
        </TableRow>
        <TableRow>
          <MTableCell>Division</MTableCell>
          <MTableCell><CodeHl>-1/(-1);</CodeHl></MTableCell>
          <MTableCell><CodeHl>1;</CodeHl></MTableCell>
        </TableRow>
        <TableRow>
          <MTableCell>Modulation</MTableCell>
          <MTableCell><CodeHl>4%3;</CodeHl></MTableCell>
          <MTableCell><CodeHl>1;</CodeHl></MTableCell>
        </TableRow>
        <TableRow>
          <MTableCell>Exponentiation</MTableCell>
          <MTableCell><CodeHl>2^3;</CodeHl></MTableCell>
          <MTableCell><CodeHl>8;</CodeHl></MTableCell>
        </TableRow>
        <TableRow>
          <MTableCell>Radication</MTableCell>
          <MTableCell><CodeHl>4^(1/2);</CodeHl></MTableCell>
          <MTableCell><CodeHl>2;</CodeHl></MTableCell>
        </TableRow>
        <TableRow>
          <MTableCell>Parenthesis</MTableCell>
          <MTableCell><CodeHl>5-(8-3)</CodeHl></MTableCell>
          <MTableCell><CodeHl>0;</CodeHl></MTableCell>
        </TableRow>
      </TableBody>
    </Table>
    <Typography
    variant="h5"
    my="1rem"
    sx={{
      fontWeight:"bold"
    }}>
      Miscellaneous
    </Typography>
    <Typography paragraph>
      To define comment: <CodeHl>// A line comment</CodeHl>
    </Typography>
  </Box>
}
