import type {
  Props
} from './Types.tsx'

export function CodeHl({children}: Props) {
  return <span
  style={{
    color:"gold",
    fontFamily:"monospace",
    fontSize:"1rem",
    backgroundColor:"#111",
    padding:"0.2rem 0.3rem"
  }}>
    {children}
  </span>
}
