import { createFileRoute } from '@tanstack/react-router'

export const Route = createFileRoute('/doc')({
  component: RouteComponent,
})

function RouteComponent() {
  return <>
    <title>Documentation</title>
    <p>jivgfniafjdaojbtuijfaodsjvihjerafojiovjfdahiofurhginfdoajfidkljfkdsajv</p>
  </>
}
